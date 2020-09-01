<?php

namespace App\Controller;

use App\Entity\Temperature;
use DateTime;
use DateTimeZone;
use Doctrine\ORM\EntityManagerInterface;
use PhpParser\Node\Stmt\Echo_;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

class PostTemperatureController extends AbstractController
{
    /**
     * @Route("/post/temperature", name="post_temperature")
     */
    public function index(Request $request, EntityManagerInterface $manager)
    {
        $content = $request->getContent();

        if (!$content) {
            throw new \Exception("No content");
        }

        $contentBody = json_decode($content, true);

        $payload = array_key_exists("payload_fields", $contentBody) ? $contentBody["payload_fields"] : null;
        $metadata = array_key_exists("metadata", $contentBody) ? $contentBody["metadata"] : null;
        
        $celsius = $payload["degreesC"];
        $time = new DateTime('now', new DateTimeZone("Europe/Brussels"));
        
        $temperature = new Temperature();
        $temperature->setCelsius($celsius);
        $temperature->setCreatedAt($time);

        $manager->persist($temperature);
        $manager->flush();

        $response = new JsonResponse([], Response::HTTP_OK);
        $response-> setContent(json_encode([
            "success" => true,
            "celsius" => $celsius,
            "time" => $time,
        ]));
        
        return $response;
    }
}
